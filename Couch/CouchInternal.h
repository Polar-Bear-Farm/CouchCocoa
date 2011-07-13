//
//  CouchInternal.h
//  CouchCocoa
//
//  Created by Jens Alfke on 6/26/11.
//  Copyright 2011 Couchbase, Inc. All rights reserved.
//

#import "Couch.h"
#import "RESTInternal.h"


@interface CouchAttachment (Private)
- (id) initWithRevision: (CouchRevision*)revision 
                   name: (NSString*)name
                   type: (NSString*)contentType;
@end


@interface CouchDatabase (Private)
- (void) documentAssignedID: (CouchDocument*)document;
- (void) receivedChangeLine: (NSData*)chunk;
@end


@interface CouchDocument (Private)
@property (readwrite, copy) NSString* currentRevisionID;
- (void) loadCurrentRevisionFrom: (NSDictionary*)contents;
- (void) bulkSaveCompleted: (NSDictionary*) result;
- (BOOL) notifyChanged: (NSDictionary*)change;
@end


@interface CouchRevision (Private)
- (id) initWithDocument: (CouchDocument*)document revisionID: (NSString*)revisionID;
- (id) initWithDocument: (CouchDocument*)document contents: (NSDictionary*)contents;
- (id) initWithOperation: (RESTOperation*)operation;
@property (readwrite) BOOL isDeleted;
@property (readwrite, copy) NSDictionary* contents;
@end


/** A query that allows custom map and reduce functions to be supplied at runtime.
    Usually created by calling -[CouchDatabase slowQueryWithMapFunction:]. */
@interface CouchFunctionQuery : CouchQuery
{
    NSDictionary* _viewDefinition;
}

- (id) initWithDatabase: (CouchDatabase*)db
         viewDefinition: (struct CouchViewDefinition)definition;

@end
